#pragma once

class SampleData {
public:
    // Populates the in-memory extents with a coherent demo graph.
    // Runs only when no data was restored, so a saved database is never overwritten.
    static void seedIfEmpty();
};
