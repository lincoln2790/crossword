#ifndef CURSOR_HPP
#define CURSOR_HPP
class cursor_t{
	public:
		word_t *word;
		std::list<tile_t>::iterator tile_it;
		cursor_t(word_t *start_word);
};
#endif
