BOB_VERSION := 3251ca82359cf238a1074e383281e3126547d50b
BOB_STAGE := stable
BOB_FILE := /tmp/bob.$(BOB_VERSION).jar

$(BOB_FILE):
	@echo "Download bob.jar"
	@wget 'http://d.defold.com/archive/$(BOB_STAGE)/$(BOB_VERSION)/bob/bob.jar' -O $(BOB_FILE)

buildandroid: $(BOB_FILE)
	@echo "Build android (APK)"
	@java -jar $(BOB_FILE) \
		--settings game.project \
		--bundle-output dist \
		--build-report-html build/report.html \
		--variant debug \
		--archive \
		--architectures armv7-android,arm64-android \
		--bundle-format apk \
		--platform armv7-android \
		resolve clean distclean build bundle