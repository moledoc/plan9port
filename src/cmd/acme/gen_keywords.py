#!/usr/bin/env python3
import re
import sys
from pathlib import Path


def extract_lang(content):
	m = re.search(r"struct\s+keyword_(\w+)", content)
	if not m:
		raise ValueError("Could not find struct keyword_<lang>")
	return m.group(1)


def extract_keywords(content):
	parts = content.split("%%")
	if len(parts) < 3:
		raise ValueError("Invalid gperf file format")

	body = parts[1]

	keywords = []
	for line in body.splitlines():
		line = line.strip()

		if not line:
			continue
		if line.startswith("#"):
			continue

		keywords.append(line)

	return keywords


def generate_header(lang, keywords):
	guard = f"KWS_{lang.upper()}_H"

	out = []
	out.append(f"#ifndef {guard}")
	out.append(f"#define {guard}")
	out.append("")
	out.append("#ifdef __cplusplus")
	out.append('extern "C" {')
	out.append("#endif")
	out.append("")
	out.append(f"static const char *keywords_{lang}[] = {{")

	for kw in keywords:
		out.append(f'	"{kw}",')

	out.append("};")
	out.append("")
	out.append(f"static const unsigned int keywords_{lang}_count = {len(keywords)};")
	out.append("")
	out.append("#ifdef __cplusplus")
	out.append("}")
	out.append("#endif")
	out.append("")
	out.append(f"#endif /* {guard} */")

	return "\n".join(out)


def main():
	if len(sys.argv) != 2:
		print("Usage: script.py <input.gperf>")
		sys.exit(1)

	input_path = Path(sys.argv[1])
	content = input_path.read_text()

	lang = extract_lang(content)
	keywords = extract_keywords(content)

	header = generate_header(lang, keywords)

	output_path = input_path.parent / f"keywords_{lang}.h"
	output_path.write_text(header)

	print(f"Generated {output_path} with {len(keywords)} keywords")


if __name__ == "__main__":
	main()