struct aggregate {
	unsigned long long first;
	unsigned long long second;
	unsigned long long third;
};
void api_large(struct aggregate record, int marker);
struct aggregate api_return(int marker);
