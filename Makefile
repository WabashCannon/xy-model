
PRO   = XYModel.pro
QMAKE = /home/ashton/Qt/5.4/gcc_64/bin/qmake

all:	QtMakefile
	$(MAKE) -f QtMakefile

clean:
	rm -fr QtMakefile QtMakefile.debug QtMakefile.release debug release

QtMakefile:
	$(QMAKE) -o QtMakefile $(PRO) CONFIG+=debug_and_release

debug:	QtMakefile
	$(MAKE) -f QtMakefile debug

release:	QtMakefile
	$(MAKE) -f QtMakefile release

.PHONY: all clean debug clean-debug release clean-release
