using Graph = vector<vector<int>>;
class Condensator {
private:
    Graph graph_, reversed_;
    vector<char> visited_;
    vector<int> color_;
    int current_color_ = 0;
    stack<uint32_t> vertex_order_;

    // Kosaraju Algorithm
    void FillVertexOrder(uint32_t cur) {
        visited_[cur] = 1;
        for (uint32_t next : graph_[cur]) {
            if (!visited_[next]) {
                FillVertexOrder(next);
            }
        }

        vertex_order_.push(cur);
    }

    void PaintVertexes(uint32_t cur) {
        color_[cur] = current_color_;
        for (uint32_t next : reversed_[cur]) {
            if (color_[next] == -1) {
                PaintVertexes(next);
            }
        }
    }

public:
    Condensator(const Graph& g)
        : graph_(g)
        , reversed_(Graph(g.size()))
        , visited_(vector<char>(g.size(), 0))
        , color_(vector<int>(g.size(), -1))
    {
        for (size_t i = 0; i < g.size(); ++i) {
            for (uint32_t j : g[i]) {
                reversed_[j].push_back(i);
            }
        }
    }

    pair<Graph, vector<vector<int>>> Condensate() {
        for (size_t v = 0; v < graph_.size(); ++v) {
            if (!visited_[v]) {
                FillVertexOrder(v);
            }
        }

        for (; !vertex_order_.empty(); vertex_order_.pop()) {
            if (color_[vertex_order_.top()] == -1) {
                PaintVertexes(vertex_order_.top());
                ++current_color_;
            }
        }

        Graph condensation(static_cast<size_t>(current_color_));
        vector<vector<int>> mapping_to_colors(current_color_);

        for (size_t v = 0; v < graph_.size(); ++v) {
            size_t a = static_cast<size_t>(color_[v]);
            mapping_to_colors[a].push_back(v);
            for (uint32_t u : graph_[v]) {
                size_t b = static_cast<size_t>(color_[u]);
                if (a != b) {
                    condensation[a].push_back(b);
                }
            }
        }

        return { condensation, mapping_to_colors };
    }
};