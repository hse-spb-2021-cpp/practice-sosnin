#include <iostream>
#include <sstream>
#include <string>

int main() {
    const std::string kHolmes =
        "I had had so many reasons to believe in my friend's subtle powers of\n"
        "reasoning and extraordinary energy in action that I felt that he "
        "must\n"
        "have some solid grounds for the assured and easy demeanour with "
        "which\n"
        "he treated the singular mystery which he had been called upon to\n"
        "fathom. Once only had I known him to fail, in the case of the King "
        "of\n"
        "Bohemia and of the Irene Adler photograph; but when I looked back to\n"
        "the weird business of the Sign of Four, and the extraordinary\n"
        "circumstances connected with the Study in Scarlet, I felt that it "
        "would\n"
        "be a strange tangle indeed which he could not unravel.";

    std::cout << kHolmes << std::endl;
    std::cout << std::endl;

    const std::string kCat = R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.)";

    std::cout << kCat << std::endl;

    return 0;
}