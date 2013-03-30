
char * single_digit_oct_to_bin (char oct_dig);
char * single_digit_dec_to_bin (char dec_dig);
char * single_digit_hex_to_bin (char hex_dig);

char single_digit_bin_to_oct (char * bin_dig);
char single_digit_bin_to_dec (char * bin_dig);
char single_digit_bin_to_hex (char * bin_dig);

char * oct_to_bin (char * oct);
char * dec_to_bin (char * dec);
char * hex_to_bin (char * hex);

char * bin_add (char * bin_one, char * bin_two);
char * bin_sub (char * bin_one, char * bin_two);

void bin_to_dec (char * bin);
char * bin_to_even_base (char * bin, int size_of_digit);