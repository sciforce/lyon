#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lyon.h"

#define EPS 0.01

START_TEST (test_soscascade)
{
  int nSamples = 5;
  int nChannels = 2;
  double *signal = (double *)malloc(sizeof(double) * nSamples);
  double *coeffs = (double *)malloc(sizeof(double) * nChannels * 5);
  double *state = (double *)malloc(sizeof(double) * nChannels * 2);
  double *output = (double *)malloc(sizeof(double) * nChannels * nSamples);

  // Input:
  // -0.50	-0.50	-0.70	-1.10	-1.70
  for (int i = 0; i < nSamples; ++i)
    signal[i] = -0.5 + i / (double) 10.0 - i * i / (double) 10.0;
  for (int i = 0; i < nChannels * 5; ++i)
    coeffs[i] = i / (double) 100.0;
  for (int i = 0; i < nChannels * 2; ++i)
    state[i] = 0.0;
  int result = soscascade(signal, nSamples, coeffs, state,
			  nChannels, output);
  // Flag
  ck_assert(result == 0);
  // State:
  // -0.07	-0.06	
  // -0.00	-0.00
  ck_assert(fabs(state[0] - (-0.07)) < EPS);
  ck_assert(fabs(state[3] - (0.00)) < EPS);
  // Output:
  // 0.00	-0.01	-0.03	-0.03	-0.05	
  // 0.00	-0.00	-0.00	-0.00	-0.00
  ck_assert(fabs(output[0] - (0.00)) < EPS);
  ck_assert(fabs(output[2] - (-0.01)) < EPS);
  free(signal);
  free(coeffs);
  free(state);
  free(output);
}
END_TEST

START_TEST (test_agc)
{
  int nSamples = 5;
  int nChannels = 2;
  int nStages = 3;
  double *output = (double *)malloc(sizeof(double) * nChannels * nSamples);
  double *agcParams = (double *)malloc(sizeof(double) * 2 * nStages);
  double *agcState = (double *)malloc(sizeof(double) * nChannels * nStages);
  double *agcOut = (double *)malloc(sizeof(double) * nChannels * nSamples);

  for (int i = 0; i < nChannels * nSamples; ++i)
    output[i] = 0.1 * i;
  for (int i = 0; i < 2 * nStages; ++i)
    agcParams[i] = 0.5;
  for (int i = 0; i < nChannels * nStages; ++i)
    agcState[i] = 0.0;
  int result = agc(output, nChannels, nSamples, nStages, agcParams, agcState, agcOut);
  // Flag
  ck_assert(result == 0);
  // State:
  // 0.64	0.41	0.30	
  // 0.66	0.42	0.30
  ck_assert(fabs(agcState[0] - (0.64)) < EPS);
  ck_assert(fabs(agcState[5] - (0.30)) < EPS);
  // Output:
  // 0.00	0.20	0.19	0.15	0.15	
  // 0.10	0.22	0.19	0.15	0.15
  ck_assert(fabs(agcOut[0] - (0.00)) < EPS);
  ck_assert(fabs(agcOut[2] - (0.20)) < EPS);
  free(output);
  free(agcParams);
  free(agcState);
  free(agcOut);
}
END_TEST

START_TEST (test_sosfilters)
{
  int nSamples = 5;
  int nChannels = 2;
  int nStages = 3;
  double *coeffs = (double *)malloc(sizeof(double) * nChannels * 5);
  double *state = (double *)malloc(sizeof(double) * nChannels * 2);
  double *output = (double *)malloc(sizeof(double) * nChannels * nSamples);
  double *agcOut = (double *)malloc(sizeof(double) * nChannels * nSamples);

  for (int i = 0; i < nChannels * 5; ++i)
    coeffs[i] = i / (double) 100.0;
  for (int i = 0; i < nChannels * 2; ++i)
    state[i] = 0.0;
  for (int i = 0; i < nChannels * nSamples; ++i)
    agcOut[i] = 0.1 * i;

  printf("Testing sosfilters...\n");
  int result = sosfilters(agcOut, nChannels, nSamples, coeffs, nChannels,
			  state, output, nChannels);
  // Flag
  ck_assert(result == 0);
  // State:
  // 0.04	0.03
  // 0.06	0.04
  ck_assert(fabs(state[0] - (0.04)) < EPS);
  ck_assert(fabs(state[2] - (0.03)) < EPS);
  // Output:
  // 0.00	0.00	0.00	0.02	0.03	
  // 0.00	0.01	0.02	0.04	0.05
  ck_assert(fabs(output[0] - (0.00)) < EPS);
  ck_assert(fabs(output[7] - (0.04)) < EPS);

  free(coeffs);
  free(state);
  free(output);
  free(agcOut);
}
END_TEST

Suite *lyon_suite(void)
{
  Suite *s;
  TCase *tc_core;
  s = suite_create("auditory-lib");
  tc_core = tcase_create("filters");
  tcase_add_test(tc_core, test_soscascade);
  tcase_add_test(tc_core, test_agc);
  tcase_add_test(tc_core, test_sosfilters);
  suite_add_tcase(s, tc_core);
  return s;
}

int main()
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = lyon_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
