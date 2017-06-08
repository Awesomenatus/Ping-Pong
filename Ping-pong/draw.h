#ifndef H_DRAW
#define H_DRAW
#include <vector>


		void Draw_field(std::vector<char>& PlayingField,
              		  int xPlayingField,
              		  int yPlayingField);
								
		bool Draw_win(int BallY, int yPlayingField);


#endif