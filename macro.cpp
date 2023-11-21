#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream inputFile("macro_input.txt");
	string line;

	map<string,int> MNT;
	map<int, string> MDT;

	vector<string> args;
	vector<string> mntOrder;
	vector<string> ALA;

	int MDTP =0;
	bool isMacro =false;
	bool isMacroFirstLine =true;
	while (getline(inputFile, line))
	{
		string originalLine =line;
		replace(originalLine.begin(), originalLine.end(), ',', ' ');
		replace(line.begin(), line.end(), ',', ' ');
		vector<string> parts;
		istringstream iss(line);
		while (iss >> line) {
			parts.push_back(line);
		}

		if (parts[0]=="MACRO")
		{
			isMacro =true;
			isMacroFirstLine =true;
			continue;
		}

		if (parts[0]=="MEND")
		{
			isMacro =false;
			isMacroFirstLine =false;
			args.clear();
			MDT[MDTP++] = originalLine;
			continue;
		}

		if (isMacroFirstLine)
		{
			isMacroFirstLine =false;
			mntOrder.push_back(parts[0]);
			MNT[parts[0]] = MDTP;

			for (int i=1; i<parts.size(); i++)
			{
				args.push_back(parts[i]);
			}

			MDT[MDTP++] = originalLine;
			continue;
		}

		if (isMacro)
		{
			// to replace agrs wiht hashtag args
			for (int i=0; i<args.size(); i++)
			{
				for (int j=0; j<parts.size(); j++)
				{
					if (args[i]==parts[j]) parts[j] ="#"+to_string(i+1);
				}
			}

			// construct new string with hashtag args
			string temp ="";
			for (int i=0; i<parts.size(); i++)
				temp +=parts[i]+" ";
			MDT[MDTP++] =temp;
			continue;
		}

		for (int i=0; i<mntOrder.size();i++)
		{
			string temp ="";
			if (parts[0]==mntOrder[i])
			{
				ALA.push_back(originalLine);
			}
		}

	}

	cout << endl << "MNT: " << endl;
	for (int i=0; i<mntOrder.size() ; i++)
	{
		cout << i << "\t" << mntOrder[i] << "\t" << MNT[mntOrder[i]] << endl;
	}
	cout << endl << "MDT: " << endl;
	for (auto& pair: MDT)
		cout << pair.first << "\t" << pair.second << endl;

	cout << endl << "ALA: " << endl;
	for (int i=0; i<ALA.size(); i++)
	{
		istringstream iss(ALA[i]); string temp;
		vector<string> parts;
		while (iss>>line)
			parts.push_back(line);

		cout << parts[0] << endl;
		for (int i=1; i<parts.size(); i++)
		{
			cout << i-1 << "\t" <<  parts[i] << endl;
		}
		cout << endl;
	}
}