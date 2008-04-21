rm *.ode
rm *.log
rm *.dat

echo "*************  converting to ode files ...."
echo
for i in *.cps; do  
echo $i;
../../copasi/CopasiSE/CopasiSE --exportXPPAUT $i.ode $i >/dev/null; 
done

echo
echo "************ running xppaut ....."
echo
for i in *.ode; do 
echo $i; rm output.dat 2>/dev/null; 
xppaut -silent $i > $i.log; 
cp output.dat $i.dat; 
echo
done

echo
echo "***********  analysing results ...."
echo
for i in *.dat; do
#echo `basename $i cps.ode.dat`csv;
../tablediff $i `basename $i cps.ode.dat`csv;
echo
done
  