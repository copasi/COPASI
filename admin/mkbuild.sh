          copasi@gorbag.bioinformatics.vt.edu:www/integrator/snapshots/$license/Copasi-AllSE/$1-Dynamic/CopasiSE-$build
      fi
      
      tar -czf ../Copasi-$build-$1-Dynamic.tar.gz copasi
    fi

    cd ..
    ;;
  esac

  scp Copasi-$build-$1*.* \
    copasi@gorbag.bioinformatics.vt.edu:www/integrator/snapshots/$license

else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
