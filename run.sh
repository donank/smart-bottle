if [ ! -d "$build" ]; then
  mkdir build
fi
cd build
cmake ../main
cmake --build .
sudo ./main