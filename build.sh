echo "Building..."
g++ ./src/example.cpp -O3 -Wall -o ./build/artemis -I ./include -std=c++17
echo "Built"
chmod 755 ./build/artemis
echo "Changed permission"
echo "Running..."
./build/artemis
echo "Done"