Under Mac OS X once mono has been installed, I can change to the examples directory and compile an example like this:

gmcs -r:../COPASI.dll -out:example1.exe example1.cs

Running the compiled example works like this:

MONO_PATH=.. mono ./example1.exe
