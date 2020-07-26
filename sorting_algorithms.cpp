const int N = 1e6 + 1;
int a[N];
int b[N]; //extra array

void mergesort(int l, int r) {
    if (r - l + 1 < 2)
        return;
    
    int cur = (l + r) / 2;
    
    mergesort(l, cur);
    mergesort(cur + 1, r);
    
    merge(a + l, a + cur + 1, a + cur + 1, a + r + 1, b);
    
    for (int i = l; i <= r; i++)
        a[i] = b[i - l];
}

void quicksort(int l, int r) {
    if (l >= r)
        return;
    srand(time(0));
    
    int ind = ((rand() << 16) + rand()) % (r - l) + l;
    int val = a[ind];
    int ll = l, rr = r;
    
    while (ll <= rr) {
        while (a[ll] < val)
            ll++;    
        while (a[rr] > val)
            rr--;
        
        if (ll > rr)
            break;
        
        swap(a[ll], a[rr]);
        ++ll;
        --rr;
    }
    
    quicksort(l, rr);
    quicksort(ll, r);
}

template<typename Iter, typename Converter>
void counting_sort(Iter begin, Iter end, Converter converter, size_t MAX = 0) {
    using T = typename std::iterator_traits<Iter>::value_type;
    if (MAX == 0)
        for (auto i = begin; i != end; ++i)
            MAX = std::max(MAX, static_cast<size_t>(converter(*i)));
    std::vector<std::list<T>> buckets(MAX + 1);
    for (auto i = begin; i != end; ++i)
        buckets[converter(*i)].push_back(*i);
    Iter i = begin;
    for (const auto& sorted_elements : buckets)
        for (const T& element : sorted_elements)
            (*(i++)) = element;
}
