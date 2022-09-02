FROM python:3.10

WORKDIR /app

COPY ./main.py .

RUN pip install prometheus-client

CMD ["python", "main.py"]
