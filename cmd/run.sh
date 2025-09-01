clear
cd ../build
cmake ..
make
cd ..
# Explicitly unset GDK_BACKEND for this execution (this removes the warning and makes the window decoration style consistent with the system decoration style)
unset GDK_BACKEND
echo
./bin/G3CE