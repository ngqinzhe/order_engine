docker build -t gemini_interview . && docker run --rm --workdir /app/build -v "$(pwd):/app" gemini_interview bash -c "cmake .. && make && ctest"