const { sbox } = require('./sbox');
const size = sbox.length;

// create 2d array filled with zeroes
const ddt = Array(size)
	.fill(null)
	.map(() => Array(size).fill(0));

for (let i = 0; i < size; i++) {
	// iterate over input difference
	for (let u0 = 0; u0 < size; u0++) {
		// iterate over first input
		let u1 = u0 ^ i, // calculate first input
			v0 = sbox[u0], // calculate sbox outputs
			v1 = sbox[u1];

		ddt[i][v0 ^ v1]++; // increment frequency in DDT for v0 xor v1
	}
}

/**
 *
 * @param {number[][]} ddt
 */
const countZeroes = ddt =>
	ddt
		.map(row => row.reduce((a, v) => a + Number(v === 0), 0))
		.reduce((a, v) => a + v, 0);

/**
 * Number of times x occurs for input difference diff in ddt
 * @param {number[][]} ddt
 * @param {number} diff
 * @param {number} x
 */
const countPerInputDiff = (ddt, diff, x) =>
	ddt[diff].reduce((a, v) => a + Number(v === x), 0);

/**
 * Number of times x occurs for output difference diff in ddt
 * @param {number[][]} ddt
 * @param {number} diff
 * @param {number} x
 */
const countPerOutputDiff = (ddt, diff, x) =>
	ddt.map(row => row[diff]).reduce((a, v) => a + Number(v === x), 0);

const max = ddt
	.slice(1)
	.map(row => row.slice(1))
	.map(row => row.reduce((p, a) => Math.max(p, a), 0))
	.reduce((p, a) => Math.max(p, a), 0);

console.log(`Max value in DDT is ${max}`);

for (let i = 0; i < size; i++) {
	console.log(
		`Number of 4s for input diff ${i.toString(16)}: `,
		countPerInputDiff(ddt, i, 4),
	);
}
for (let i = 0; i < size; i++) {
	console.log(
		`Number of 2s for input diff ${i.toString(16)}: `,
		countPerInputDiff(ddt, i, 2),
	);
}

for (let i = 0; i < size; i++) {
	console.log(
		`Number of 4s for output diff ${i.toString(16)}: `,
		countPerOutputDiff(ddt, i, 4),
	);
}
for (let i = 0; i < size; i++) {
	console.log(
		`Number of 2s for output diff ${i.toString(16)}: `,
		countPerOutputDiff(ddt, i, 2),
	);
}

console.log('Zeroes:', countZeroes(ddt));
