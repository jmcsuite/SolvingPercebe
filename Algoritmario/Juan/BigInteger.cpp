const int BASE = 1e9;
struct BigInteger {
  vll digits;

  BigInteger() {
    digits.clear();
    digits.push_back(0);
  }
  BigInteger(ll number) {
    digits.clear();
    do {
      digits.push_back(number % BASE);
      number /= BASE;
    } while (number);
  }

  BigInteger operator+(const BigInteger &b) const {
    BigInteger res = BigInteger();
    res.digits.resize(max(b.digits.size(), digits.size()));
    ll remainder = 0;
    for (size_t i = 0; i < res.digits.size(); i++) {
      if (i < digits.size()) remainder += digits[i];
      if (i < b.digits.size()) remainder += b.digits[i];
      res.digits[i] = remainder % BASE;
      remainder /= BASE;
    }
    while (remainder) {
      res.digits.push_back(remainder % BASE);
      remainder /= BASE;
    }
    return res;
  }

  BigInteger operator*(const BigInteger &b) const {
    BigInteger res = BigInteger();
    if (digits.size() == 1 && digits[0] == 0) return {0};
    if (b.digits.size() == 1 && b.digits[0] == 0) return {0};
    res.digits = vector<ll>(b.digits.size() + digits.size() - 1, 0);
    for (size_t i = 0; i < digits.size(); i++)
      for (size_t j = 0; j < b.digits.size(); j++)
        res.digits[i + j] += digits[i] * b.digits[j];
    ll remainder = 0;
    for (size_t i = 0; i < res.digits.size(); i++) {
      remainder += res.digits[i];
      res.digits[i] = remainder % BASE;
      remainder /= BASE;
    }
    while (remainder) {
      res.digits.push_back(remainder % BASE);
      remainder /= BASE;
    }
    return res;
  }

  void print() {
    cout << digits.back();
    for (int i = digits.size() - 2; i >= 0; i--)
      cout << setw(9) << setfill('0') << digits[i];
  }

  static BigInteger power(const BigInteger &b, ll k) {
    if (k == 0) return BigInteger(1);
    if (k == 1) return b;
    BigInteger res = power(b, k / 2);
    res = res * res;
    if (k & 1) return res * b;
    return res;
  }

  bool operator<(const BigInteger &b) const {
    if (digits.size() != b.digits.size())
      return digits.size() < b.digits.size();
    for (int i = digits.size() - 1; i >= 0; i--) {
      if (digits[i] != b.digits[i]) return (digits[i] < b.digits[i]);
    }
    return false;
  }
};
