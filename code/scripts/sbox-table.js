const { sbox } = require('./sbox');
const nums = Array(16)
	.fill(0)
	.map((_, i) => i.toString(16));

console.log(`\\begin{tabular}{|r||${'r|'.repeat(16)}}
\\hline`);

console.log(`  & ${nums.map(v => v.padStart(2, '0')).join(' & ')} \\\\
\\hline  \\hline`);

for (let i = 0; i < 16; i++) {
	let row = `${nums[i].padEnd(2, '0')}`;

	for (let j = 0; j < 16; j++) {
		const out = sbox[i * 16 + j];
		row += ` & ${out.toString(16).padEnd(2, '0')}`;
	}
	console.log(`${row} \\\\
\\hline`);
}

console.log(`\\end{tabular}`);
