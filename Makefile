CC = g++
CFLAGS = -g -std=c++11
SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_DIR = ./tests
SAMPLES = $(TEST_DIR)/sample_programs

RED = \033[031m
GREEN = \033[032m
YELLOW = \033[033m
BLUE = \033[034m
CLR_RESET = \033[0m

TARGET = file_lexer.exe
LEXER_TEST = lexer_test.exe

all: $(TARGET)

$(TARGET): lexer.o
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.cpp $(OBJ_DIR)/$^

lexer.o: object_dir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lexer.cpp
	mv $@ $(OBJ_DIR)

object_dir:
	mkdir -p $(OBJ_DIR)

lexer_test: $(LEXER_TEST)
	@echo "\n$(BLUE)---------------------- Running test 1 ----------------------$(CLR_RESET)\n"
	@./$< < $(SAMPLES)/test1.txt
	@echo "\n$(BLUE)---------------------- Running test 2 ----------------------$(CLR_RESET)\n"
	@./$< < $(SAMPLES)/test2.txt
	@echo "\n$(BLUE)---------------------- Running test 3 ----------------------$(CLR_RESET)\n"
	@./$< < $(SAMPLES)/test3.txt
	@echo "\n$(BLUE)---------------------- Running test 4 ----------------------$(CLR_RESET)\n"
	@./$< < $(SAMPLES)/test4.txt
	@echo "\n$(BLUE)---------------------- Running test 5 ----------------------$(CLR_RESET)\n"
	@./$< < $(SAMPLES)/test5.txt

$(LEXER_TEST): lexer.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/lexer_tests.cpp $(OBJ_DIR)/$<

clean:
	@rm -f -r $(OBJ_DIR)
	@rm -f $(LEXER_TEST)
	@rm -f $(TARGET)
	@echo "$(GREEN)Cleaning complete$(CLR_RESET)"