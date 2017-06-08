#ifndef H_FILL_VECTOR
#define H_FILL_VECTOR
#include <vector>

	void Fill_vector_platform(std::vector<char>& PlayingField,
														int Coordinate,
														int Length,
														int yPlayingField,
														int Position);

	void Fill_vector_border(std::vector<char>& PlayingField,
													int xPlayingField,
													int yPlayingField);

	void Fill_vector_ball(std::vector<char>& PlayingField,
												int xBall,
												int yBall,
												int yPlayingField);

	void Fill_vector_all_space(std::vector<char>& PlayingField,
												 int xPlayingField,
												 int yPlayingField);

	void Fill_vector_space(std::vector<char>& PlayingField, int pos);

#endif