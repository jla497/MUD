
#include <gtest/gtest.h>

#include "i18n/i18n.h"

TEST(I18nTest, Init_NotActuallyATest) {
	i18n::init();
}

TEST(I18nTest, EnglishWorks) {
	ASSERT_STREQ(i18n::get(StrKey::ACTION_PROGRAM, LangKey::EN_US).c_str(), "program");
}

TEST(I18nTest, SmurflangWorks) {
	ASSERT_STREQ(i18n::get(StrKey::ACTION_PROGRAM, LangKey::_TESTING_SMURF_).c_str(), "smurfprogram");
}

TEST(I18nTest, SmurflangMissingDefersDefault) {
	ASSERT_STREQ(i18n::get(StrKey::ACTION_SWAP, LangKey::_TESTING_SMURF_).c_str(), "swap");
}

TEST(I18nTest, MissingString) {
	ASSERT_STREQ(i18n::get(StrKey::_N_STRINGS_, LangKey::EN_US).c_str(), i18n::DEFAULT_STRING);
}
