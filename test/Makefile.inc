TEST_DIR = $(TOP_DIR)/test

# Define common codes used for the tests
TEST_COMMON = tst_utils.o
TEST_COMMON := $(addprefix $(TEST_DIR)/, $(TEST_COMMON))

TEST_EXE_  = tst_simple tst_sp tst_dp tst_mem
TEST_EXE_ += tst_char
TEST_EXE_ += tst_type
TEST_EXE_ += tst_dict tst_dict_long
TEST_EXE_ += tst_dict_mem1 tst_dict_mem2
TEST_EXE_ += tst_dict_mem3 tst_dict_mem4
TEST_EXE_ += tst_dict_overwrite
TEST_EXE_ += tst_dict_remove
TEST_EXE_ += tst_dict_dict tst_dict_speed
TEST_EXE_ += tst_dict_hash

TEST_EXE ?= $(TEST_EXE_)

ifeq ($(STATIC),1)
  TEST_LIB    = libvardict.a
else
  ifeq ($(SHARED),1)
    TEST_LIB  = libvardict.so
  else
    $(error No library is build, the tests cannot be performed.)
  endif
endif

# Create correct dependency schemes without adding too
# many flags in the direct compilation targets.
# Ensure the common utility is compiled before any test
$(call addpresuf ,$(TEST_DIR)/,.o,$(TEST_EXE)): $(TEST_COMMON)
# Ensure the executables depend on the utility and the library
$(TEST_EXE): $(TEST_COMMON) $(TEST_LIB)
# Ensure the src/ directory is included in the search path
# for modules
$(TEST_EXE): INCLUDES += -I$(VSRC_DIR)
# Ensure the test directory gets the modules
$(TEST_EXE): FFLAGS += $(FC_MODDIR)$(TEST_DIR)


# Add source includes

.PHONY: test
.NOTPARALLEL: test
test: $(TEST_LIB) $(TEST_EXE)


tst_simple: $(TEST_DIR)/tst_simple.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_char: $(TEST_DIR)/tst_char.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_sp: $(TEST_DIR)/tst_sp.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dp: $(TEST_DIR)/tst_dp.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_mem: $(TEST_DIR)/tst_mem.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_type: $(TEST_DIR)/tst_type.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict: $(TEST_DIR)/tst_dict.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_speed: $(TEST_DIR)/tst_dict_speed.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_long: $(TEST_DIR)/tst_dict_long.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_hash: $(TEST_DIR)/tst_dict_hash.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_mem1: $(TEST_DIR)/tst_dict_mem1.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_mem2: $(TEST_DIR)/tst_dict_mem2.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_mem3: $(TEST_DIR)/tst_dict_mem3.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_mem4: $(TEST_DIR)/tst_dict_mem4.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_overwrite: $(TEST_DIR)/tst_dict_overwrite.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_remove: $(TEST_DIR)/tst_dict_remove.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

tst_dict_dict: $(TEST_DIR)/tst_dict_dict.o
	$(FC) -o $(TEST_DIR)/$@ $(FFLAGS) $(INCLUDES) $^
	./$(TEST_DIR)/$@

.PHONY: clean-test
clean-test:
	-rm -f $(addprefix $(TEST_DIR)/,$(TEST_EXE) $(LIB_TEST) $(TEST_COMMON) *.o *.mod)
clean: clean-test


# Local Variables:
#  mode: makefile-gmake
# End: