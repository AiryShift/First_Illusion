static void testReverseModulus(void);
void runTests(void);

void runTests(void) {
    testReverseModulus();
}

static void testReverseModulus(void) {
    int a = 5;
    int b = 6;
    assert(reverseModulus(a, b) == 1);
    a = 6;
    b = 2;
    assert(reverseModulus(a, b) == 0);
    assert(reverseModulus(b, a) == 3);
}
