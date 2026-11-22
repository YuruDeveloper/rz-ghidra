struct wide_record {
	unsigned long long first;
	unsigned long long second;
	unsigned long long third;
};

unsigned long long api_wide(int marker);
double api_double(int marker);
float api_float(int marker);
struct wide_record api_record(int marker);
void api_void(int marker);
