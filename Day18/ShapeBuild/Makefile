normal: ShapeComp_main.cpp ShapeComp.o 
	@echo -- Building ShapeComp.out from $^
	g++ ShapeComp_main.cpp ShapeComp.o -o ShapeComp.out

lib : ShapeComp_main.cpp libShapeComp.so
	@echo -- Building ShapeComp.out using ShapeComp.so as a shared library
	g++ ShapeComp_main.cpp -L. -lShapeComp -o ShapeComplib.out

ShapeComp.o : ShapeComp.cpp
	@echo -- Compiling $< into $@
	g++ $< -c -o $@

libShapeComp.so : ShapeComp.o
	@echo -- Building shared object ShapeComp.so from $^
	g++ --shared ShapeComp.o -o libShapeComp.so


clean:
	@echo -- Cleaning up folder
	rm -rf *.o *.so *.a *.out