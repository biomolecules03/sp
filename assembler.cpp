#include <bits/stdc++.h>
using namespace std;

struct MnemomicTable
{
	map<string, int> AD;
    map<string, int> IS;
    map<string, int> RG;
    map<string, int> CC;
    map<string, int> DL;

    MnemomicTable () {
	    AD["START"] = 01;
	    AD["END"] = 02;
	    AD["ORIGIN"] = 03;
	    AD["EQU"] = 04;
	    AD["LTORG"] = 05;

	    CC["EQ"] = 01;
	    CC["LT"] = 02;
	    CC["GT"] = 03;
	    CC["LE"] = 04;
	    CC["GE"] = 05;
	    CC["NE"] = 06;
	    CC["ANY"] = 07;

		DL["DS"] = 01;
	    DL["DC"] = 02;

	    IS["STOP"] = 00;
	    IS["ADD"] = 01;
	    IS["SUB"] = 02;
	    IS["MULT"] = 03;
	    IS["MOVER"] = 04;
	    IS["MOVEM"] = 05;
	    IS["COMP"] = 06;
	    IS["BC"] = 07;
	    IS["DIV"] = 8;
	    IS["READ"] = 9;
	    IS["PRINT"] = 10;

	    RG["AREG"] = 01;
	    RG["BREG"] = 02;
	    RG["CREG"] = 03;
	}

	int lookup(const string& part)
	{
		// check in AD map
		auto it = AD.find(part);
		if (it!=AD.end())
			return AD[part]+100;

		// check in CC map
		it = CC.find(part);
		if (it!=CC.end())
			return CC[part]+200;

		// check in DL map
		it = DL.find(part);
		if (it!=DL.end())
			return DL[part]+300;

		// check in IS map
		it = IS.find(part);
		if (it!=IS.end())
			return IS[part]+400;

		// check in RG map
		it = RG.find(part);
		if (it!=RG.end())
			return RG[part]+500;

		return -1;
	}
};

void printTable(map<string,int>& table, vector<string>& order)
{
	for (int i=0; i<order.size();i++)
	{
		cout << i << "\t" << order[i] << "\t" << table[order[i]] << endl;
	}
    cout << endl;
}

int main(){
	    ifstream inputFile("tj_input.txt");
	    string line; MnemomicTable mt;
	    map<string,int> SYMBTAB;
	    map<string,int> LITTAB;
	    map<string,int> POLTAB;

	    vector<string> symOrder;
	    vector<string> litOrder;
	    vector<string> polOrder;
	    int lctr =0;

	    while (getline(inputFile, line))
	    {
	    	// to divide line into vector element
	    	vector<string> parts;
			istringstream iss(line);
	        while (iss >> line) {
	            parts.push_back(line);
	        }	    	

	        int curr =0;
	        // check for label 
	        // if lookup return value is -1
	        // then it is label
	        if (mt.lookup(parts[curr])==-1)
	        {
	        	// check in symtable
	        	bool found =false;
				for (int i=0; i<symOrder.size(); i++)
				{
					if (symOrder[i]==parts[curr])
					{
						found =true;
						break;
					}
				}
	        	if(!found) //if not found
	        	{
	        		symOrder.push_back(parts[curr]);
	        		SYMBTAB[parts[curr]] = lctr;
	        	} else
	        	{
	        		SYMBTAB[parts[curr]] = lctr;
	        	}

	        	int i=0;
	        	for (;i<symOrder.size();i++)
	        		if (parts[curr]==symOrder[i])
	        			break;
	        	cout << "(S,0" << i<<")";
	        	curr++;
	        }

	        // check for start
	        if (parts[curr]=="START")
	        {
	        	lctr = stoi(parts[curr+1]); //stoi to convert string to int
	        	cout << "(AD,01) " << "(C," << parts[curr+1] << ")" << endl;
	        } 
	        else if (parts[curr]=="ORIGIN")
	        {
	        	lctr = SYMBTAB[parts[++curr]];
	        	istringstream iss(parts[++curr]);
	        	char sign; iss >> sign;
	        	int value; iss >> value;
	        	if (sign=='+') lctr +=value; // note: use '' not "" for comparison
	        	else lctr -=value;

	        	cout << "(AD,03) (C," << lctr-1 << ")" << endl;
	        }
	        else if (parts[curr]=="LTORG" || parts[curr]=="END")
	        {
	        	bool first =true;
	        	// if(parts[curr]=="LTORG")
	        	// 	cout << "(AD,05)" << endl;
	        	// make pool table
	        	for (int i=0; i<litOrder.size(); i++)
	        	{
	        		if (LITTAB[litOrder[i]]==-1)
	        		{
	        			polOrder.push_back(litOrder[i]);
	        			POLTAB[litOrder[i]] =lctr;
	        			break;
	        		}
	        	}

	        	// assign addr to literals
	        	for (int i=0; i<litOrder.size(); i++)
	        	{

	        		if (LITTAB[litOrder[i]]==-1)
	        		{
	        			LITTAB[litOrder[i]] =lctr++;
	        			string temp =litOrder[i];
	        			replace(temp.begin(),temp.end(),'\'',' ');
	        			replace(temp.begin(),temp.end(),'=',' ');
	        			cout << "(DL,02), (C," << temp << ")" << endl;
	        		}
	        	}

	        	if (parts[curr]=="END")
	        	{
	        		cout << "(AD,02)" << endl;
	        		break;
	        	}
	        }
	        else if(parts[curr]=="EQU")
	        {
	        	lctr++;
	        	istringstream iss(parts[curr+1]);
	        	char sign; iss >> sign;
	        	int value; iss >> value;
	        	if (sign=='+')
	        		SYMBTAB[parts[curr-1]] = SYMBTAB[parts[curr-1]] + value;
	        	else if (sign=='-')
	        		SYMBTAB[parts[curr-1]] = SYMBTAB[parts[curr-1]] - value;
	        	else
	        	{
	        		SYMBTAB[parts[curr-1]] = SYMBTAB[parts[curr+1]];
	        		// to get index from symbol table
	        		int i=0;
		        	for (;i<symOrder.size();i++)
		        		if (parts[curr+1]==symOrder[i])
		        			break;
	        		cout << "(AD,04) (S," << i << ")" <<endl;
	        		continue;
	        	}
	        	cout << "(AD,04) (C," << value << ")" <<endl;
	        }
	        else if(parts[curr]=="DS")
	        {
	        	int value =stoi(parts[curr+1]);
	        	lctr +=value;
	        	cout << "(DL,01) (C," << value << ")" << endl;
	        }
	        else if (parts[curr]=="DC")
	        {
	        	lctr++;
	        	cout << "(DL,02) (C," << parts[curr+1] << ")" << endl;
	        }
	        else if (parts[curr]=="READ")
	        {
	        	lctr++;
	        	symOrder.push_back(parts[curr+1]);
	        	// cout << parts[curr+1] << " " << parts[curr+1].size() << endl;
	        	int i=0;
	        	for (;i<symOrder.size();i++)
	        		if (parts[curr+1]==symOrder[i])
	        			break;
	        	cout << "(IS,09) (S,0" << i<<")" << endl;
	        }
	        else if (mt.lookup(parts[curr])!=-1)
	        {
	        	lctr++;
	        	int temp = mt.lookup(parts[curr++]);
	        	int classID = (temp/10)/10; // to get class of opcode
	        	int mCode = temp -classID*100; // mnemomic code
	        	// if (classID)
	        	// cout << classID << " " << mCode << endl;
	        	if (classID==4) // for IS class
	        	{
	        		if (mCode==10) // to handle PRINT
	        		{
	        			auto it =SYMBTAB.find(parts[curr]);
	        			int index = distance(SYMBTAB.begin(), it);
	        			cout << "(IS,10) (S," << index << ")" << endl;
	        			continue;
	        		} else if (mCode==0)// to handle STOP
	        		{
	        			cout << "(IS,00)" << endl;
	        			continue;
	        		}

	        		string t =parts[curr];
	        		t.pop_back(); // to remove , from end of the string
	        		temp =mt.lookup(t);
	        		classID = (temp/10)/10; // to get class of opcode
	        		// cout << t << " " << temp << " " << classID << " " << mCode <<endl;
	        		cout << "(IS,0" << mCode << ") ";
	        		if (classID==5) // RG class
	        		{
	        			istringstream iss(parts[curr++]);
	        			char t; iss >> t;
	        			cout << "(RG,0";
	        			if (t=='A')
	        			{
	        				cout << "1";
	        			}
	        			else if (t=='B')
	        			{
	        				cout << "2";
	        			}
	        			else 
	        			{
	        				cout << "3";
	        			}
	        			cout << ")";

	        			// check the operand 2 is symbol or literal or constant
	        			istringstream iss1(parts[curr]);
	        			char t1; iss1 >> t1;
	        			// string literal; iss1 >> literal1;
	        			if (t1=='=') // it is literal
	        			{
	        				// string temp =parts[curr].pop_back();
	        				litOrder.push_back(parts[curr]);
	        				LITTAB[parts[curr]]=-1;
	        				// cout << parts[curr] ;
	        				// auto it =LITTAB.find(parts[curr]);
	        				// if (it!=LITTAB.end()) cout << "F" << endl;
	        				int index =-1;
	        				for (int i=0; i<litOrder.size(); i++)
	        				{
	        					index++;
	        					string temp =to_string(LITTAB[litOrder[i]]);
	        					if (temp ==parts[curr])
	        						break;
	        				}
	        				cout << " (L,0" << index << ")" << endl;
	        			}
	        			else if (isdigit(t1)) // it is constant
	        			{
	        				cout << " (C," << parts[curr] << ")" << endl;
	        			}
	        			else // it is symbol
	        			{
	        				bool found =false;
	        				for (int i=0; i<symOrder.size(); i++)
	        				{
	        					if (symOrder[i]==parts[curr])
	        					{
	        						found =true;
	        						break;
	        					}
	        				}
	        				// cout << parts[curr] << " " << parts[curr].size() << endl;
	        				if (found)
	        				{
	        					int i=0;
		        				for (; i<symOrder.size();i++)
	        						if (symOrder[i]==parts[curr])
	        							break;
		        				cout << "(S,0" << i << ")" << endl;
		        			} else
		        			{
		        				symOrder.push_back(parts[curr]);
	        					SYMBTAB[parts[curr]];
	        					int i=0;
	        					for (; i<symOrder.size();i++)
	        						if (symOrder[i]==parts[curr])
	        							break;
		        				cout << "(S,0" << i << ")" << endl;
		        			}
	        			}
	        			
	        		}
	        		else if(classID==2) // CC class
	        		{
	        			string t= parts[curr];
	        			t.pop_back();
	        			int temp = mt.lookup(t);
			        	int classID = (temp/10)/10; // to get class of opcode
			        	int mCode = temp -classID*100;
	        			cout << "(CC,0" << mCode << ") ";
        				int i=0;
        				for (;i<symOrder.size();i++)
        					if (symOrder[i]==parts[curr+1])
	        						break;
        				cout << "(S,0" << i << ")" << endl;
	        		}
	        	}
	        }
    	}
    	cout << endl;
    	inputFile.close();
    	cout << "Symbol Table: \n";
    	printTable(SYMBTAB, symOrder);
    	cout << "Literal Table: \n";
    	printTable(LITTAB, litOrder);
    	cout << "Pool Table: \n";
    	printTable(POLTAB, polOrder);
}