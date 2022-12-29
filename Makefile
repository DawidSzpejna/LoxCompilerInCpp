BUILDDIR = Buildings
# CXXFLAGS = -Wall -fsanitize=address,undefined
CXXFLAGS =
CXX = g++
SIL ?=
DEBUG = -g


.PHONY: all parser scanner representation tokens \
		expressions main astgen cleanAst returnexception resolver


#################################################
# Rules of whole project
#################################################


all: preparedir main parser scanner tokens expressions errorcatcher commonobject \
	 runtimeerror interpreter stmt environment callablers returnexception resolver
	@$(CXX) $(DEBUG) $(CXXFLAGS) \
		$(BUILDDIR)/LoxCallable.o \
		$(BUILDDIR)/CommonObject.o \
		$(BUILDDIR)/CppLoxError.o \
		$(BUILDDIR)/Parser.o \
		$(BUILDDIR)/Scanner.o \
		$(BUILDDIR)/Token.o \
		$(BUILDDIR)/Expressions.o \
		$(BUILDDIR)/cppLox.o \
		$(BUILDDIR)/RuntimeError.o \
		$(BUILDDIR)/Interpreter.o \
		$(BUILDDIR)/Stmt.o \
		$(BUILDDIR)/Environment.o \
		$(BUILDDIR)/ReturnException.o \
		$(BUILDDIR)/Resolver.o \
		-o cpplox
	@printf "CppLox is completed\n"


preparedir:
	@mkdir -p $(BUILDDIR)


#################################################
# Subrules for the project
#################################################


main: cppLox.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) cppLox.cpp -o $(BUILDDIR)/cppLox.o

scanner: Scanner/Scanner.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Scanner/Scanner.cpp -o $(BUILDDIR)/Scanner.o

parser: Parser/Parser.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Parser/Parser.cpp -o $(BUILDDIR)/Parser.o

interpreter: Interpreter/Interpreter.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Interpreter/Interpreter.cpp -o $(BUILDDIR)/Interpreter.o

tokens: Representation/Token.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/Token.cpp -o $(BUILDDIR)/Token.o

expressions: Representation/Expressions.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/Expressions.cpp -o $(BUILDDIR)/Expressions.o

stmt: Representation/Stmt.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/Stmt.cpp -o $(BUILDDIR)/Stmt.o

environment: Representation/Environment.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/Environment.cpp -o $(BUILDDIR)/Environment.o

# prettyprint: tools/PrettyPrinter/Prettyprinter.cpp
# 	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) tools/PrettyPrinter/Prettyprinter.cpp -o $(BUILDDIR)/Prettyprinter.o

errorcatcher: Errors/CppLoxError.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Errors/CppLoxError.cpp -o $(BUILDDIR)/CppLoxError.o

commonobject: Representation/CommonObject.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/CommonObject.cpp -o $(BUILDDIR)/CommonObject.o

runtimeerror: Errors/Runtime/RuntimeError.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Errors/Runtime/RuntimeError.cpp -o $(BUILDDIR)/RuntimeError.o

callablers: Representation/LoxCallable.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Representation/LoxCallable.cpp -o $(BUILDDIR)/LoxCallable.o

returnexception: Errors/GoodErrors/ReturnException.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Errors/GoodErrors/ReturnException.cpp -o $(BUILDDIR)/ReturnException.o

resolver: Resolver/Resolver.cpp
	$(SIL)$(CXX) -c $(DEBUG) $(CXXFLAGS) Resolver/Resolver.cpp -o $(BUILDDIR)/Resolver.o


#################################################
# Rules for compiling helpful tools
#################################################


astgen: tools/ClassASTGenerator/GenerateAst.cpp
	@mkdir -p tools/ClassASTGenerator/Build tools/ClassASTGenerator/Products
	$(SIL)$(CXX) $(DEBUG) tools/ClassASTGenerator/GenerateAst.cpp -o tools/ClassASTGenerator/Build/ASTgenerator
	./tools/ClassASTGenerator/Build/ASTgenerator ./tools/ClassASTGenerator/Products/


cleanAst:
	rm ./tools/ClassASTGenerator/Products/Expr.cpp ./tools/ClassASTGenerator/Products/Stmt.cpp
