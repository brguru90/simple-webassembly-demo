#em++ -s WASM=1 -s EXPORTED_FUNCTIONS='["_c_hello","_print","_jsPrintString"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o test.js pgm.cpp
#em++ -s WASM=1 -s EXPORTED_FUNCTIONS='["_c_hello","_print","_jsPrintString"]' -s MODULARIZE=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o test.js pgm.cpp

#----------for method 1 -------------
em++ -s WASM=1   -s EXPORTED_FUNCTIONS='["_jsPrintString","_c_hello","_print"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0   -o test.js pgm.cpp

#em++ -s WASM=1  -s EXTRA_EXPORTED_RUNTIME_METHODS='["_jsPrintString"]' -s EXPORT_ALL=1  -s ERROR_ON_UNDEFINED_SYMBOLS=1  -o test.js pgm.cpp



#em++ -s WASM=1 -s EXPORT_ALL=1 -o test.js pgm.cpp

#----------for method 2 -------------
em++ pgm2.cpp -O3 -s WASM=1 -s SIDE_MODULE=1 -s EXPORTED_FUNCTIONS='["_c_hello","_print","_jsPrintString"]'  -o test2.wasm
#em++ pgm.cpp -Os -s WASM=1 -s SIDE_MODULE=1 -o test.wasm

set EMCC_DEBUG=1

# em++ -s WASM=1   -s EXPORTED_FUNCTIONS='["_test","_threadCompleteCallback"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s MODULARIZE=1 -s USE_PTHREADS=1 -s ASSERTIONS=2 -o thread.js thread2.cpp
em++ -s WASM=1   -s EXPORTED_FUNCTIONS='["_test","_threadCompleteCallback"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_PTHREADS=1 -s ASSERTIONS=2 -o thread.js thread2.cpp

em++ thread2.cpp -O3 -s WASM=1 -s SIDE_MODULE=1 -s EXPORTED_FUNCTIONS='["_test","_threadCompleteCallback"]' -s EXIT_RUNTIME=1 -o thread2.wasm
