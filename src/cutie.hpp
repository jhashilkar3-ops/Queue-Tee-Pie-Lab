#include <string>

class Cutie {
  private:
    std::string description;
    int cuteness_rating;

  public:
    Cutie(std::string description, int cuteness_rating) {
      this->description = description;
      this->cuteness_rating = cuteness_rating;
    }

    virtual std::string get_description() = 0;
    virtual int get_cuteness_rating() = 0;
}
