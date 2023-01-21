#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

typedef std::map<unsigned int, unsigned int> BraceMap;

BraceMap build_brace_map(string code)
{
	BraceMap brace_map;
	std::vector<int> brace_stack;

	for (unsigned i = 0; i < code.length(); i++)
	{
		switch (code[i])
		{
		case '[':
			brace_stack.push_back(i);
			break;
		case ']':
		{
			unsigned int last_brace = brace_stack[brace_stack.size() - 1];
			brace_stack.pop_back();

			brace_map[i] = last_brace;
			brace_map[last_brace] = i;
			break;
		}
		default:
			break;
		}
	}
	return brace_map;
}

void run_br_code(string code)
{
	BraceMap brace_map = build_brace_map(code);
	unsigned char memory[2000] = {};
	unsigned int pointer_location = 0;
	unsigned int code_location = 0;

	while (true)
	{
		if (code_location >= code.size())
		{
			// printf("Done");
			break;
		}

		switch (code[code_location])
		{

		case '+':
			memory[pointer_location]++;
			code_location++;
			break;

		case '-':
			memory[pointer_location]--;
			code_location++;
			break;

		case '>':
			pointer_location++;
			code_location++;
			break;

		case '<':
		{

			pointer_location--;
			code_location++;
			break;
		}

		case '[':
		{
			unsigned char current_value = memory[pointer_location];
			if (current_value == 0)
			{
				// jump to the matching brace
				code_location = brace_map[code_location];
			}
			else
			{
				code_location++;
			}
			break;
		}

		case ']':
		{
			unsigned char current_value = memory[pointer_location];
			if (current_value == 0)
			{
				code_location++;
			}
			else
			{
				code_location = brace_map[code_location];
			}
			break;
		}

		case '.':
		{
			unsigned char current_value = memory[pointer_location];
			printf("%c", current_value);
			code_location++;
			break;
		}

		case ',':
		{
			std::cerr << "Error: `,` is not yet implemented" << std::endl;
			code_location++;
			break;
		}

		default:
			code_location++;
			break;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: br++ file.bfpp\n";
		return 1;
	}

	// https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
	// what is this syntax
	char *file = argv[1];
	std::ifstream ifs(file);
	std::string content((std::istreambuf_iterator<char>(ifs)),
						(std::istreambuf_iterator<char>()));
	run_br_code(content);
	return 0;
}
