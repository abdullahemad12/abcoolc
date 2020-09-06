##################################
# Compiles the components of the
# Cool program and copies them 
# to bin directory
###################################

make clean -C src/lexer
make lexer -C src/lexer
make clean -C src/parser
make parser -C src/parser
make clean -C src/semant
make semant -C src/semant
make clean -C src/cgen
make cgen  -C src/cgen


