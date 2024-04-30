
import errno
import os
import sys
import shutil
import platform
import sysconfig 
from os.path import abspath, exists, join, split

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


def prepend_variables(args, variables):
  for var in variables: 
    temp = os.getenv(var)
    if temp:
      if var == 'CMAKE_GENERATOR':
        args = ['-G', temp] + args
      else:
        args.insert(0, '-D' + var + '=' +temp)
  return args

def get_python_include():
  temp = os.getenv('PYTHON_INCLUDE_DIR')
  if temp:
    return temp

  path = sysconfig.get_paths()['include']
  if exists(path): 
    return path
  # for whatever reason 2.7 on centos returns a wrong path here 
  return sysconfig.get_config_vars()['INCLUDEPY']

def get_win_python_lib():
  vars = sysconfig.get_config_vars()
  for k in ['prefix', 'installed_base', 'installed_platbase']:
    if k not in vars:
      continue
    path = os.path.join(vars[k], 'libs', 'python' + vars['py_version_nodot'] + '.lib')
    if os.path.exists(path):
      return path
  return None

def get_lib_full_path(path, partial): 
  for file in os.listdir(path): 
    if partial in file: 
      return os.path.join(path, file)
  return None

def makedirs(folder, *args, **kwargs):
  try:
    return os.makedirs(folder, exist_ok=True, *args, **kwargs)
  except TypeError: 
    # Unexpected arguments encountered 
    pass

  try:
    # Should work is TypeError was caused by exist_ok, eg., Py2
    return os.makedirs(folder, *args, **kwargs)
  except OSError as e:
    if e.errno != errno.EEXIST:
      raise

    if os.path.isfile(folder):
      # folder is a file, raise OSError just like os.makedirs() in Py3
      raise

def get_dir_if_exists(variable, default):
  value = os.getenv(variable, default)
  value = abspath(value)
  if not exists(value):
    return None
  return value

global SRC_DIR
SRC_DIR = get_dir_if_exists('COPASI_SRC_DIR', './copasi_source')
global DEP_DIR
DEP_DIR = get_dir_if_exists('COPASI_DEP_DIR', './copasi-dependencies/')
DEP_SRC_DIR = get_dir_if_exists('COPASI_DEP_SRC', './copasi-dependencies/')
DEP_DIR32 = get_dir_if_exists('COPASI_DEP_DIR_32', '../win_copasi_dependencies_32/')
DEP_DIR64 = get_dir_if_exists('COPASI_DEP_DIR_64', '../win_copasi_dependencies_64/')


if not SRC_DIR:
  src_defined = os.getenv('COPASI_SRC_DIR')
  if src_defined:
    raise ValueError("COPASI Source defined as: {0}, but couldn't be found".format(src_defined))
  else:
    raise ValueError("COPASI Source not specified or not present, define COPASI_SRC_DIR.")

print ("Using COPASI from:  {0}".format(SRC_DIR))
print ("Using Dependencies: {0}".format(DEP_DIR))

version_file_name = join(join(SRC_DIR, 'copasi'), 'CopasiVersion.h')
print ("Using version file: {0}".format(version_file_name))

if not exists(version_file_name):
  print(os.listdir(SRC_DIR))
  raise ValueError("Invalid COPASI Source directory, no version file, consider running ./gitTools/UpdateCopasiVersion.")

with open(version_file_name, 'r') as version_file:
  COPASI_VERSION_MAJOR = ''
  COPASI_VERSION_MINOR = ''
  COPASI_VERSION_BUILD = ''
  for line in version_file:
    if 'COPASI_VERSION_MAJOR' in line:
      COPASI_VERSION_MAJOR = line[line.rfind(' '):].strip()
    if 'COPASI_VERSION_MINOR' in line:
      COPASI_VERSION_MINOR = line[line.rfind(' '):].strip()
    if 'COPASI_VERSION_BUILD' in line:
      COPASI_VERSION_BUILD = line[line.rfind(' '):].strip()
  VERSION = '{0}.{1}.{2}'.format(COPASI_VERSION_MAJOR, COPASI_VERSION_MINOR, COPASI_VERSION_BUILD)

print ("Version is: {0}".format(VERSION))
print ("building for python: {0}".format(sys.version))

if not exists('COPASI'):
  makedirs('COPASI')


class CMakeExtension(Extension):
    """Override the default setuptools extension building."""

    def __init__(self, name, sources=(), **kwargs):
        """Initialize by passing on arguments."""
        # Don't invoke the original `build_ext` for this special extension.
        try: 
          super(CMakeExtension, self).__init__(name=name, sources=list(sources), **kwargs)
        except:
          Extension.__init__(self, name, list(sources), **kwargs)


class CMakeBuild(build_ext):
    """Override `build_ext` to then register it in the command classes."""

    def run(self):
        """
        Call Cmake and build every extension.

        Overrides parent's method.

        """
        for ext in self.extensions:
            self.build_cmake(ext)
        try: 
            super(CMakeBuild, self).run()
        except:
            build_ext.run(self)

    def build_cmake(self, extension):
        """Configure `extension` with CMake and build modules."""
        cwd = os.getcwd()
        build_temp = self.build_temp
        suffix = build_temp[build_temp.find('temp.') + 5:]
        if '/' in suffix:
          suffix = suffix[:suffix.rfind('/')]
        if '\\' in suffix:
          suffix = suffix[:suffix.rfind('\\')]

        ext_dir = self.get_ext_fullpath(extension.name)
        makedirs(build_temp)
        target_lib_path = abspath(ext_dir)
        target_dir_path, name = split(target_lib_path)
        makedirs(target_dir_path)
        makedirs(join(cwd, 'copasi'))

        print ('name: {0}'.format(name))
        print ('build temp: {0}'.format(build_temp))
        print ('extension name: {0}'.format(extension.name))
        print ('extension dir: {0}'.format(ext_dir))
        print ('target_dir_path: {0}'.format(target_dir_path))
        print ('target_lib_path: {0}'.format(target_lib_path))
        print ('suffix: {0}'.format(suffix))
        print ('cwd: {0}'.format(cwd))

        # get config from environment or set default
        config = os.getenv('CMAKE_BUILD_TYPE')
        if not config:
          config = 'Debug' if self.debug else 'Release'
        
        print ('name: {0}, tmp: {1}'.format(name, build_temp))
        is_osx = platform.system() == 'Darwin'
        is_win = platform.system() == 'Windows'
        is_win_32 = is_win and ('win32' in name or 'win32' in build_temp)
        enable_jit = 'ON' if ('_64' in suffix or 'amd64' in suffix) else 'OFF'
        enable_clapack = 'OFF' if is_osx else 'ON'

        cmake_args = [
            '-DCMAKE_BUILD_TYPE=' + config
        ]

        if is_win: 
          cmake_args.append('-DWITH_STATIC_RUNTIME=ON')

        cmake_args = prepend_variables(cmake_args, [
          'CMAKE_CXX_COMPILER', 
          'CMAKE_C_COMPILER', 
          'CMAKE_LINKER', 
          'CMAKE_GENERATOR',
          'CMAKE_OSX_ARCHITECTURES',
          'CMAKE_SYSTEM_PROCESSOR'
        ])

        if is_win_32:
          if not '-G' in str(cmake_args):
            cmake_args.append('-A')
            cmake_args.append('win32')

        if is_osx: 
          if 'arm64' in suffix: 
            cmake_args.append('-DCMAKE_OSX_ARCHITECTURES=arm64')
          else:
            cmake_args.append('-DCMAKE_OSX_ARCHITECTURES=x86_64')

        # example of build args
        build_args = [
            '--config', config,
            '--'
        ]

        global DEP_DIR
        if DEP_DIR and exists(DEP_DIR) and not self.dry_run:
            print("compiling dependencies")
            dep_suffix = sysconfig.get_platform()
            dep_inst_dir = os.path.join(cwd, 'install_dependencies_' + dep_suffix)
            if not exists(dep_inst_dir):
               dep_build_dir = os.path.join(cwd, 'build_dependencies_' + dep_suffix)
               dep_src_dir = DEP_SRC_DIR
               makedirs(dep_build_dir)
               os.chdir(dep_build_dir)
               self.spawn(['cmake', dep_src_dir] + cmake_args
                         + [
                             '-DCMAKE_INSTALL_PREFIX=' + dep_inst_dir,
                             '-DBUILD_UI_DEPS=OFF',
                             '-DBUILD_zlib=ON',
                             '-DBUILD_archive=OFF',
                             '-DBUILD_NativeJIT=' + enable_jit,
                             '-DBUILD_clapack=' + enable_clapack,
                             '-DBUILD_uuid=ON'
                           ]
                         )
               self.spawn(['cmake', '--build', '.'] + build_args)
               os.chdir(cwd)
            DEP_DIR = dep_inst_dir

        copasi_args = [
            '-DBUILD_GUI=OFF',
            '-DENABLE_PYTHON=ON',
            '-DPYTHON_EXECUTABLE=' + sys.executable,
            '-DPYTHON_INCLUDE_DIR=' + get_python_include(),
            '-DENABLE_JIT=' + enable_jit
        ]

        if 'emscripten' in suffix:
          copasi_args += [                                      
            '-DDATAVALUE_NEEDS_SIZE_T_MEMBERS=1' ,
            '-DDISABLE_STACK_PROTECTOR=ON', 
            '-DF2C_INTEGER=int',
            '-DF2C_LOGICAL=int',
            '-DDISABLE_CORE_OBJECT_LIBRARY=ON',
          ]

        copasi_args = prepend_variables(copasi_args, [
          'SWIG_DIR',
          'SWIG_EXECUTABLE'
        ])

        if not is_win:
          copasi_args.append('-DPYTHON_USE_DYNAMIC_LOOKUP=ON')
        else:
          lib_path = get_win_python_lib()
          if lib_path is not None:
            copasi_args.append('-DPYTHON_LIBRARY={0}'.format(lib_path))

        if not is_win and not is_osx:
          copasi_args.append('-DCMAKE_CXX_FLAGS=-fPIC')

        cmake_args = cmake_args + copasi_args

        if DEP_DIR:
          cmake_args.append('-DCOPASI_DEPENDENCY_DIR=' + DEP_DIR)

        if is_win_32:
          if DEP_DIR32:
            cmake_args.append('-DCOPASI_DEPENDENCY_DIR=' + DEP_DIR32)
        elif is_win:
          if DEP_DIR64:
            cmake_args.append('-DCOPASI_DEPENDENCY_DIR=' + DEP_DIR64)

        if enable_clapack:
          # we need to replace the headers in the dependencydir/include
          for header in ['f2c.h', 'blaswrap.h']:
            src = os.path.join(SRC_DIR, 'copasi', 'lapack', header)
            dst = os.path.join(DEP_DIR, 'include', header)
            if exists(src) and exists(dst):
              shutil.copyfile(src, dst)

        os.chdir(build_temp)
        self.spawn(['cmake', SRC_DIR] + cmake_args)
        if not self.dry_run:
            self.spawn(['cmake', '--build', '.', '--target', 'binding_python_lib'] + build_args)

            # at this point the build should be complete, and we have all the files 
            # neeed in the temp build_folder

            init_py2 = None
            init_py3 = None
            dst_file = join(target_dir_path, '__init__.py')

            for root, dirs, files in os.walk(".", topdown=False):
              for name in files:
                # 1. find pyd and copy to target_lib_path
                if name.endswith('.pyd') or name == '_COPASI.so' or name == '_COPASI.dylib':
                  pyd_file = join(root, name)
                  print('copying pyd file to output file')
                  shutil.copyfile(pyd_file, target_lib_path)
                # 2. get scripts and copy to target_lib_path.parent.__init__.py corresponding to version 
                if name == 'COPASI.py':
                  src_file = join(root, name)
                  shutil.copyfile(src_file, dst_file)
                if name == 'COPASI2.py':
                  init_py2 = join(root, name)
                if name == 'COPASI3.py':
                  init_py3 = join(root, name)

            if init_py2 and exists(init_py2) and sys.version_info.major == 2:
                  shutil.copyfile(init_py2, dst_file)

            if init_py3 and exists(init_py3) and sys.version_info.major == 3:
                  shutil.copyfile(init_py3, dst_file)

        os.chdir(cwd)


setup(name             = "python-copasi", 
      version          = VERSION,
      description      = "COPASI Python API",
      long_description = ("COPASI is a software application for simulation and analysis of biochemical networks and their dynamics. COPASI is a stand-alone program that supports models in the SBML standard and can simulate their behavior using ODEs or Gillespie's stochastic simulation algorithm; arbitrary discrete events can be included in such simulations."),
      license          = "Artistic License",
      author           = "COPASI Team",
      author_email     = "copasi-devel@copasi.org",
      url              = "http://copasi.org",
      packages         = ["COPASI"],
      package_dir      = {'COPASI': 'COPASI'},
      ext_package      = "COPASI",
      ext_modules=[CMakeExtension('_COPASI')],
      cmdclass={
        'build_ext': CMakeBuild,
      }
)
