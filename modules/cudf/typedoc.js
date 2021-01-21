module.exports = {
    entryPoints: ['src'],
    out: 'doc',
    name: '@nvidia/cudf',
    tsconfig: 'tsconfig.json',
    excludePrivate: true,
    excludeProtected: true,
    excludeExternals: true,
};