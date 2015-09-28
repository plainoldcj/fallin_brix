// gamestate.cpp

#include "gamestate.h"

Gamestate::score_t Gamestate::score;

Gamestate::score_t& Gamestate::GetScore(void)
{
	if(score.empty())
	{
		char buffer[512];
		std::ifstream file("res/score.txt");

		if(!file.is_open())
		{
			for(int i = 0; i < 10; ++i)
			{
				score.push_back(scoreEntry_t(std::string("-empty-"), 0));
			}
			return score;
		}

		while(!file.eof())
		{
			file.getline(buffer, 512);
			std::string line(buffer);
			if(line.length() <= 1) continue;
			int at = line.find(' ', 0);
			std::string name = line.substr(0, at);
			line.erase(0, at);
			std::stringstream sstream;
			int numScore;
			sstream << line;
			sstream >> numScore;
			score.push_back(scoreEntry_t(name, numScore));
		}
		file.close();
	}
	return score;
}

void Gamestate::WriteScore(void)
{
	std::ofstream file("res/score.txt", std::ios::trunc);
	for(score_t::iterator scoreIt(score.begin()); scoreIt != score.end(); ++scoreIt)
	{
		file << scoreIt->first << " " << scoreIt->second << std::endl;
	}
	file.close();
}