#ifndef __ITERATOR_CATEGORY_HPP
#define __ITERATOR_CATEGORY_HPP

namespace Ave {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
};

#endif
