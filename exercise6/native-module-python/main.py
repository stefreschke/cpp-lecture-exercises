
# Import process function from pre-built cffi module
process = Null

from cffi import FFI


if __name__=="__main__":
	for i in range(1, 101):
		print("Call with", i, "results in", process(i))

