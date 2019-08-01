#!/bin/sh
PORT=9000

for task in pwn*; do
	hash=$(docker image build --quiet "$task")

	printf '%s: %s\n', "$task" "$hash"
	docker container create \
		--publish "$PORT:12345" \
		--name "$task" \
		"$hash"

	PORT=$((PORT + 1))
done
