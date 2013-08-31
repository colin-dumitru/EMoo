OUT_DIR=../out

FILES=
for file in $(find `pwd` -iname '*.h'); do 
     FILES=$FILES\ $file
done
echo $FILES

cd OUT_DIR
llvm-g++-4.7 -emit-llvm -c $FILES