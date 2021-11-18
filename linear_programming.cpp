using Double = long double;
using Inequality = vector<Double>;

class InequalitySystemSolver {
private:
	vector<Inequality> inequalities_;
	Double inf = INT64_MAX;

public:

	InequalitySystemSolver() = default;

	InequalitySystemSolver(const vector<Inequality>& inequalities) {
		reserve(inequalities.size());
		for (const Inequality& ineq : inequalities) {
			push_back(ineq);
		}
	}

	void reserve(size_t capacity) { inequalities_.reserve(capacity); }

	void push_back(Inequality ineq) {
		Double lambda = 1;
		if (ineq.back() > 0) {
			lambda = ineq.back();
		}
		else if (ineq.back() < 0) {
			lambda = -ineq.back();
		}

		for (Double& d : ineq)
			d /= lambda;
		inequalities_.push_back(ineq);
	}


	vector<Double> GetSolution() {  // Returns empty vector is there's no solution
		if (inequalities_[0].size() == 2) {  // Only 1 variable
			Double l = -inf, r = inf;
			for (const Inequality& ineq : inequalities_) {
				// ineq[0] +- x >= 0
				if (ineq[1] > 0) {
					l = max(l, -ineq[0]);
				}
				else if (ineq[1] < 0) {
					r = min(r, ineq[0]);
				}
				else {
					if (ineq[0] < 0) {
						return {};
					}
				}
			}
			if (l > r) {
				return {};
			}
			return { r };
		}

		vector<Inequality> plus, minus, zero;
		for (const Inequality& ineq : inequalities_) {
			if (ineq.back() > 0) {
				plus.push_back(ineq);
				plus.back().pop_back();
			}
			else if (ineq.back() < 0) {
				minus.push_back(ineq);
				minus.back().pop_back();
			}
			else {
				zero.push_back(ineq);
				zero.back().pop_back();
			}
		}

		InequalitySystemSolver new_iss;
		new_iss.reserve(zero.size() + plus.size() * minus.size());
		for (const Inequality& ineq : zero)
			new_iss.push_back(ineq);

		for (const Inequality& ineq1 : plus) {
			for (const Inequality& ineq2 : minus) {
				Inequality ineq3 = ineq1;
				for (size_t i = 0; i < ineq1.size(); ++i)
					ineq3[i] += ineq2[i];
				new_iss.push_back(ineq3);
			}
		}

		vector<Double> result = new_iss.GetSolution();
		if (result.empty()) {
			return {};
		}

		Double r = inf;

		for (const Inequality& ineq : minus) {
			Double sum = ineq[0];
			for (size_t i = 1; i < ineq.size(); ++i)
				sum += ineq[i] * result[i - 1];
			r = min(r, sum);
		}

		result.push_back(r);
		return result;
	}
};