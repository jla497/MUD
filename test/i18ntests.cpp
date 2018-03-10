
#include <gtest/gtest.h>

#include "i18n/i18n.h"

TEST(I18nTest, Init_NotActuallyATest) {
	i18n::init();
}

TEST(I18nTest, EnglishWorks) {
	ASSERT_STREQ(i18n::get(LangKey::EN_US, StrKey::ACTION_PROGRAM).c_str(), "program");
}

TEST(I18nTest, SmurflangWorks) {
	ASSERT_STREQ(i18n::get(LangKey::_TESTING_SMURF_, StrKey::ACTION_PROGRAM).c_str(), "smurfprogram");
}

TEST(I18nTest, SmurflangMissingDefersDefault) {
	ASSERT_STREQ(i18n::get(LangKey::EN_US, StrKey::ACTION_SWAP).c_str(), "swap");
}

TEST(I18nTest, MissingString) {
	ASSERT_STREQ(i18n::get(LangKey::EN_US, StrKey::_N_STRINGS_).c_str(), i18n::DEFAULT_STRING);
}
