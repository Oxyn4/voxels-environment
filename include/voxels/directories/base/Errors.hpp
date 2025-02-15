#pragma once

namespace voxels::directories {
    enum ValidationError {
        PermissionError,
        DoesNotExist,
        NotDirectoryError
    };

    enum GetCandidateError {
        NoCandidate
    };
}
