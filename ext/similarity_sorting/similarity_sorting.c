
#include <ruby.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

VALUE SimilaritySorting = Qnil;

VALUE method_similarity_sorting_sort(VALUE self, VALUE array, VALUE scores, VALUE lookahead);

void Init_similarity_sorting() {
  SimilaritySorting = rb_define_module("SimilaritySorting");

  rb_define_singleton_method(SimilaritySorting, "sort", method_similarity_sorting_sort, 3);
}

void sort_block(VALUE array, VALUE scores, long start, long stop) {
  int i;

  for(i = start + 1; i < stop; i++) {
    VALUE reference = rb_ary_entry(array, i - 1);
    VALUE reference_keywords_array = rb_ary_entry(reference, 2);

    long max_index = i;
    double max_value = -1;
    long u;

    for(u = i; u < stop; u++) {
      VALUE current = rb_ary_entry(array, u);
      VALUE current_keywords_hash = rb_ary_entry(current, 1);
      long keywords_count = RARRAY_LEN(reference_keywords_array);
      double value = 0;
      long k;

      for(k = 0; k < keywords_count; k++) {
        VALUE keyword = rb_ary_entry(reference_keywords_array, k);

        if(rb_hash_lookup(current_keywords_hash, keyword) == Qtrue)
          value += NUM2DBL(rb_ary_entry(scores, NUM2LONG(keyword)));
      }

      if(value > max_value) {
        max_index = u;
        max_value = value;
      }
    }

    VALUE old = rb_ary_entry(array, i);
    rb_ary_store(array, i, rb_ary_entry(array, max_index));
    rb_ary_store(array, max_index, old);
  }
}

VALUE method_similarity_sorting_sort(VALUE self, VALUE array, VALUE scores, VALUE lookahead) {
  long len = RARRAY_LEN(array);
  long lookahead_value = NUM2LONG(lookahead);
  long b;

  for(b = 0; b < len; b += lookahead_value)
    sort_block(array, scores, b, MIN(len, b + lookahead_value));

  for(b = lookahead_value / 2; b < len; b += lookahead_value)
    sort_block(array, scores, b, MIN(len, b + lookahead_value));

  return array;
}

