fpconv=https://github.com/night-shift/fpconv.git

googletest_release=release-1.8.0

googletest_archive=$(googletest_release).zip

googoletest_unziped=googletest-$(googletest_release)

googletest=https://github.com/google/googletest/archive/$(googletest_archive)

install: install_fpconv install_googletest

install_fpconv:
	git clone $(fpconv)
	./install_fpconv.sh

install_googletest:
	curl -LOk $(googletest)
	unzip $(googletest_archive)
	rm -f $(googletest_archive)
	mv ./$(googoletest_unziped)/googletest ./googletest
	mv ./$(googoletest_unziped)/googlemock ./googlemock
	rm -R -f googletest-$(googletest_release)

remove_fpconv:
	rm -R -f fpconv

remove_googletest:
	rm -R -f googletest googlemock

remove: remove_googletest remove_fpconv
