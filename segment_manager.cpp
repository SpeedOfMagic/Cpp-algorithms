class SegmentManager {
private:
	int united_length_ = 0;
	set<pair<int, int>> segments_rl_;

public:
	int AddSegment(int l, int r) {
		int border_intersection = 0;
		for (auto iter = segments_rl_.lower_bound({ l, -1 }); iter != segments_rl_.end();
			iter = segments_rl_.lower_bound({ l, -1 })) {
			int other_l = (*iter).second, other_r = (*iter).first;
			if (other_l < l) {  // other_l...l
				if (r < other_r) {  // other_l...l...r...other_r
					return border_intersection;
				} else {  // other_l...l...other_r...r
					++border_intersection;
					united_length_ -= other_r - other_l;
					l = other_l;
				}
			} else {  // l...other_l
				if (other_l <= r) {  // l...other_l...r
					++border_intersection;
					if (other_r <= r) {  // l...other_l...other_r...r
						++border_intersection;
						united_length_ -= other_r - other_l;
					} else { // l...other_l...r...other_r
						united_length_ -= other_r - other_l;
						r = other_r;
					}
				} else {  // l...r...other_l...other_r
					break;
				}
			}
			segments_rl_.erase(iter);
		}
		segments_rl_.insert({ r, l });
		united_length_ += r - l;
		return border_intersection;
	}

	constexpr int GetUnitedLength() const { return united_length_; }

	inline bool HasPoint(int point) const {
		auto iter = segments_rl_.lower_bound({ point, -1 });
		return (iter != segments_rl_.end() && (*iter).second <= point);
	}
	
    set<pair<int, int>>& GetSegmentsRL() const { return segments_rl_; }
};
