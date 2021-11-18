class SlidingWindow {
private:
	const std::vector<int>& vector_;

	std::deque<int> min_deque_;
	
	size_t left_border_ = 0, right_border_;

public:
	SlidingWindow(const std::vector<int>& vector, size_t window_size)
	: vector_(vector)
	, right_border_(window_size) {
		for (size_t i = 0; i < window_size; ++i) {
			while (!min_deque_.empty() && min_deque_.back() < vector[i])
				min_deque_.pop_back();
			min_deque_.push_back(vector[i]);
		}
	}

	void MoveRight() {
		if (vector_[left_border_] == min_deque_.front())
			min_deque_.pop_front();

		if (right_border_ < vector_.size()) {
			while (!min_deque_.empty() && min_deque_.back() < vector_[right_border_])
				min_deque_.pop_back();
			min_deque_.push_back(vector_[right_border_]);
		}

		++left_border_; ++right_border_;
	}

	inline int GetMin() const {
		return min_deque_.front();
	}
};