
#include <ruby.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

VALUE SimilaritySorting = Qnil;

VALUE method_similarity_sorting_sort(VALUE self, VALUE array, VALUE scores, VALUE start, VALUE stop);

void Init_similarity_sorting() {
  SimilaritySorting = rb_define_module("SimilaritySorting");

  rb_define_singleton_method(SimilaritySorting, "sort", method_similarity_sorting_sort, 4);
}

VALUE method_similarity_sorting_sort(VALUE self, VALUE array, VALUE scores, VALUE start, VALUE stop) {
  long len = RARRAY_LEN(array);
  long start_value = NUM2LONG(start);
  long stop_value = NUM2LONG(stop);
  long b, i;

  for(i = start_value + 1; i <= stop_value; i++) {
    VALUE reference = rb_ary_entry(array, i - 1);
    VALUE reference_keywords_array = rb_ary_entry(reference, 2);

    long max_index = i;
    double max_value = -1;
    long u;

    for(u = i; u <= stop_value; u++) {
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

  return Qnil;
}

