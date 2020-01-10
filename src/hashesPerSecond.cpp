#include <stdio.h>
#include <stdint.h>
#include <string>
#include <chrono>
#include "pha/pha.hpp"
#include "sha2/sha2.hpp"

void testSHA256(char * input, uint length = 1, uint secs=1) {

	printf("Testing sha256...\n");

	uint64_t count = 0;
	unsigned char result[PHA256_CHAR_DIGEST_SIZE] = {0};

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	do {
		sha256((const unsigned char *) input, length, result);
		count += 1;
		elapsed = std::chrono::high_resolution_clock::now() - start;
	} while (elapsed.count() < (double) secs);

	const uint64_t blocks = (length / SHA256_BLOCK_SIZE + 1);

	printf("SHA-256: %.15lf hashes/s/block\n", (double)(count) / elapsed.count() * blocks);
}

void testPHA256(char * input, uint length = 1, uint secs=1) {

	printf("Testing pha256...\n");

	uint64_t count = 0;
	char result[PHA256_CHAR_DIGEST_SIZE] = {0};
	PHA256 pha = PHA256();

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	do {
		pha.digest(result, input, length);
		count += 1;
		elapsed = std::chrono::high_resolution_clock::now() - start;
	} while (elapsed.count() < (double) secs);

	const uint64_t blocks = (length / PHA256_CHAR_BLOCK_SIZE + 1);

	printf("PHA-256: %.15lf hashes/s/block\n", (double)(count) / elapsed.count() * blocks);
}


void testPHA512(char * input, uint length = 1, uint secs=1) {

	printf("Testing pha512...\n");

	uint64_t count = 0;
	char result[PHA512_CHAR_DIGEST_SIZE];
	PHA512 pha = PHA512();

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	do {
		pha.digest(result, input, length);
		count += 1;
		elapsed = std::chrono::high_resolution_clock::now() - start;
	}while (elapsed.count() < (double) secs);

	const uint64_t blocks = (length / PHA512_CHAR_BLOCK_SIZE + 1);

	printf("PHA-512: %.15lf hashes/s/block\n", (double)(count) / elapsed.count() * blocks);
}


int main() {

	uint length = 1024 * 1024; // 1 MiB
	uint seconds = 10;
	char * input = 0;

	while (length == 0) {
		printf("Enter the length  (greater than 0): ");
		scanf("%u", &length);
	}

	while (seconds == 0) {
		printf("Enter the seconds (greater than 0): ");
		scanf("%u", &seconds);
	}

	input = new char[length];

	testSHA256(input, length, seconds);
	testPHA256(input, length, seconds);
	testPHA512(input, length, seconds);

	delete [] input;

	return 0;
}
