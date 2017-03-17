#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include <fstream>
class Score
{
	int *score;
public:
	Score();
	~Score();
	int* get_s(){	return score;	}
	void write_s();
	void read_s();
};
Score::Score(void)
{
	score = new int[4];
	score[0] = score[1] = score[2] = score[3] = 0;
}
Score::~Score()
{
	delete []score;
}
void Score::write_s()
{
	std::ofstream outfile;
	outfile.open("Score",std::ios::out);
	outfile << score[2];
	outfile.close();
}
void Score::read_s()
{
	std::ifstream infile;
	infile.open("Score",std::ios::in);
	infile >> score[1];
	infile.close();
}

#endif // SCORE_H_INCLUDED
