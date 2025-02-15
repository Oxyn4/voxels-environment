#pragma once

namespace Directories {
    enum ValidationError {
        PermissionError,
        DoesNotExist,
        NotDirectoryError
    };

    enum GetCandidateError {
        NoCandidate
    };
}
