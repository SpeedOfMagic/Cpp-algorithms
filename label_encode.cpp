vector<vector<int>> LabelEncode(vector<vector<int>> objects, size_t total = 0) {
	if (total == 0)
		for (const auto& vec : objects)
			total += vec.size();

	struct triple {
		int obj;
		size_t i, j;
		bool operator<(const triple& other) const { return obj < other.obj; }
	};
	vector<triple> all;
	all.reserve(total);
	for (size_t i = 0; i < objects.size(); ++i)
		for (size_t j = 0; j < objects[i].size(); ++j)
			all.push_back({ objects[i][j], i, j });
	sort(all.begin(), all.end());

	int num = 0;
	for (size_t i = 0; i < all.size(); ++i) {
		num += i && (all[i].obj != all[i - 1].obj);
		objects[all[i].i][all[i].j] = num;
	}
	return objects;
}
