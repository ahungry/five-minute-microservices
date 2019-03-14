FROM openjdk:8-alpine

COPY target/uberjar/luminus-webserver.jar /luminus-webserver/app.jar

EXPOSE 3000

CMD ["java", "-jar", "/luminus-webserver/app.jar"]
