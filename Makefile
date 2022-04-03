TARGET = ./main.out
TARGET_TEST = ./test.out
HDRS_DIR = project/include

SRCS =  project/src/main.c\
        project/src/utils.c\
        project/src/prints.c\
		project/src/functions_for_cases.c

.PHONY: all build rebuild check build_my_test run_my_test test memtest clean

SRCS_TEST = project/src/test_module.c\
			project/src/functions_for_cases.c\
			project/src/utils.c\
			project/src/prints.c

all: clean check test memtest

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

my_test: build_my_test run_my_test

$(TARGET_TEST): $(SRCS_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)

build_my_test: $(TARGET_TEST)

run_my_test: test.out
	./test.out

rebuild: clean build

check:
	./run_linters.sh
    
test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat
