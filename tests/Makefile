TEST_SUITE = kernel
TESTS = console string

test: build-tests atffile run-tests

build-tests:
	for test in $(TESTS); do			\
		$(CC) -o $$test.o -c $$test.c;		\
		$(CC) -o $$test $$test.o -latf-c;	\
	done

atffile:
	rm Atffile; 									\
	echo "Content-Type: application/X-atf-atffile; version=\"1\"" > Atffile;	\
	echo "" >> Atffile;								\
	echo "prop: test-suite = $(TEST_SUITE)" >> Atffile;				\
	for test in $(TESTS); do							\
		echo "tp: $$test" >> Atffile;						\
	done

run-tests:
	atf-run | atf-report
